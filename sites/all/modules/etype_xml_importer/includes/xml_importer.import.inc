<?php
require_once('Encoding.php');
use \ForceUTF8\Encoding;  // It's namespaced now.
/**
 * Create Entity
 * @param array $item
 * @param array $values
 * @param string $entity_type
 */
function etype_xml_importer_entity_create($item = array(), $values = array(), $entity_type = 'node') {

  $entity = entity_create($entity_type, $values);
  $wrapper = entity_metadata_wrapper($entity_type, $entity);
  $node_type = variable_get('etype_xml_node_type', 'article');
  $subhead_field = variable_get('etype_xml_subhead_field', 'field_subhead');
  $subhead_format = variable_get('etype_xml_subhead_format', 'plain_text');
  $pullquote_format = variable_get('etype_xml_pulled_quote_format', 'plain_text');

  if (count($item) > 0) {
    $title = 'no title found';
    foreach ($item as $k => $v) {
      switch ($k) {
        case 'title':
          $title = $v;
          $wrapper->$k->set($v);
          break;

        case 'body':

          if (isset($item['summary'])) {
            $wrapper->body->set(array(
                'value' => $v,
                'summary' => $item['summary'],
                'format' => 'full_html'
              )
            );
          } else {
            $wrapper->body->set(array(
                'value' => $v,
                'format' => 'full_html'
              )
            );
          }
          break;

        case 'field_pulled_quote':

          if (field_info_instance('node', "field_pulled_quote", $node_type)) {
            switch ($pullquote_format) {
              case 'full_html':
                $wrapper->field_pulled_quote->set(array(
                    'value' => $v,
                    'format' => 'full_html'
                  )
                );
                break;

              default:
                $wrapper->field_pulled_quote->set($v);
            }
          }
          break;

        case $subhead_field:
          switch ($subhead_format) {
            case 'full_html':
              $wrapper->$subhead_field->set(array(
                  'value' => $v,
                  'format' => 'full_html'
                )
              );
              break;

            default:
              $wrapper->$subhead_field->set($v);
          }
          break;

        case 'summary':
          break;

        case 'images':
          //$fields = field_info_field_map();
          $files = array();
          // print_r($v);
          foreach ($v as $arr) {
            /* Files coming from Olive named the same, gives duplicate entry error for file_managed table */
            $rand = substr(md5(uniqid(mt_rand(), true)), 0, 10);
            $file = file_save_data(file_get_contents($arr['path']), 'public://' . $rand . '_' . $arr['name']);
            $file->display = '1';
            $file->description = $arr['caption'];
            /* Set caption if image field caption enabled, otherwise set
            title */
            if (module_exists('image_field_caption')) {
              $file->image_field_caption = array(
                'value' => $arr['caption'],
                'format' => 'plain_text'
              );
            } else {
              /* remove whitespace and truncate to fit */
              $fixed = preg_replace('/\s+/', ' ', $arr['caption']);
              $trimmed = substr($fixed, 0, 255);
              $file->title = $trimmed;
            }
            $file = file_save($file);
            $file = (array) $file;
            $files[] = $file;
          }
          // print_r($files);
          $wrapper->field_image->set($files);
          break;

        default:
          if (field_info_instance('node', "$k", $node_type)) {
            $wrapper->$k->set($v);
          }
      }
    }
    // try to continue and not stop the whole import
    try {
      if (!$wrapper->save(TRUE)) {
        throw new Exception("Wrapper not saved");
      }
    } catch(Exception $e) {
      watchdog('etype_xml_importer', "Import failed for \"$title\".", $variables = [], $severity = WATCHDOG_NOTICE);
    }
  }
}

/**
 * Parse Olive XML Files
 */
function etype_xml_importer_olive_import() {

  global $user;
  $import_files = variable_get('etype_xml_import_file');
  if (empty($import_files)) {
    watchdog('etype_xml_importer', "XML import setting empty.", $variables = array(), $severity = WATCHDOG_NOTICE);
    return;
  }

  // Settings
  $byline_field = variable_get('etype_xml_byline_field', 'field_dateline');
  $subhead_field = variable_get('etype_xml_subhead_field', 'field_subhead');

  // Import URL, with commented out testing option, and check for trailing slash
  // $base_import_url = 'http://test.etypegoogle4.com/xml-import/';
  $base_import_url = variable_get('etype_xml_base_import_url', 'http://olivexml.etypeservices.com/olivexml/');
  if (substr($base_import_url, -1) !== '/') {
    $base_import_url = $base_import_url . '/';
  }
  $import_file_array = explode(',', $import_files);

  if (count($import_file_array) > 0) {

    $i = 0;
    foreach ($import_file_array as $item) {

      // echo $item;
      $rand = md5(time());
      $zip_file = "/tmp/" . $rand . ".zip";
      $extract_dir = '/tmp/' . $rand . '/';

      /* Copy Zip file from url */
      $import_file = $base_import_url . trim($item);
      if (!file_put_contents($zip_file, file_get_contents($import_file))) {
        watchdog('etype_xml_importer', "Could not import " . $import_file . ".", $variables = array(), $severity = WATCHDOG_WARNING);
        continue;
      }

      /* Extract Zip Archive */
      $zip = new ZipArchive;
      $res = $zip->open($zip_file);
      if ($res === TRUE) {
        $zip->extractTo($extract_dir);
        $zip->close();
      } else {
        watchdog('etype_xml_importer', "eType XML Importer could not open Zip Archive %file", $variables = array('%file' => $zip_file), $severity = WATCHDOG_WARNING);
        exit;
      }

      /* Loop over directory and get the Files */
      $fileSystemIterator = new FilesystemIterator($extract_dir);
      $entries = array();
      foreach ($fileSystemIterator as $fileInfo) {
        $entry = $fileInfo->getFilename();
        if(strpos($entry, 'Section') !== FALSE) {
          $entries[] = $fileInfo->getFilename();
        }
      }

      /* Loop over found files and do the extraction */
      if (count($entries) > 0) {

        $node_type = variable_get('etype_xml_node_type', 'article');
        $values = array(
          'type' => $node_type,
          'uid' => $user->uid,
          'status' => 0,
          'comment' => 0,
          'promote' => 0,
          'language' => LANGUAGE_NONE,
        );

        foreach ($entries as $entry) {
          $xml = file_get_contents($extract_dir . $entry);
          if ($xml !== FALSE) {
            /* parse xml in each file */
            $obj = simplexml_load_string($xml, 'SimpleXMLElement', LIBXML_NOCDATA);
            if (sizeof($obj) > 0) {
              /* loop over items in Section file */
              foreach ($obj as $stub) {
                $item = $stub->item;
                /* xml object processing of stub which contains link, title, and description */
                foreach ($item as $k => $v) {
                  $array = (array) $v;
                  // print_r($array);
                  // title is not an object if the stub is valid
                  if (!is_object($array['title'])) {
                    // full article is in the linked file
                    $ar_file =  $array['link'];
                    $ar_xml = file_get_contents($extract_dir . $ar_file);

                    /* parse article xhtml from link file */
                    preg_match("/<prism:section>([^<]+)/", $ar_xml, $coincidencias);
                    /* ignore classifieds? */
                    $etype_xml_import_classifieds = variable_get('etype_xml_import_classifieds');
                    // echo $etype_xml_import_classifieds;
                    if ($etype_xml_import_classifieds !== 1) {
                      if ($coincidencias[1] == 'Classifieds') {
                        continue;
                      }
                    }
                    $array['section'] = $coincidencias[1];

                    preg_match("/<dc:title>([^<]+)/", $ar_xml, $coincidencias);
                    // echo 'title should be: ' . $coincidencias[1] . "\n";
                    $array['title'] = substr($coincidencias[1], 0, 255);

                    preg_match("/<prism:coverDate>([^<]+)/", $ar_xml, $coincidencias);
                    $array['pub_date'] = $coincidencias[1];

                    // s flag makes dot match linebreaks as well
                    preg_match("'<body>(.*?)</body>'s", $ar_xml, $coincidencias);
                    $body = $coincidencias[1];
                    $body = preg_replace("'<xhtml:h1>(.*?)</xhtml:h1>'s","", $body);
                    $body = preg_replace("'<pam:media>(.*?)</pam:media>'s","", $body);
                    $body = preg_replace("'<xhtml:p prism:class=\"deck\">(.*?)</xhtml:p>'s", "", $body, 1);
                    $body = preg_replace("'<xhtml:p prism:class=\"byline\">(.*?)</xhtml:p>'s", "", $body, 1);
                    $body = preg_replace("/xhtml:([a-z]?)/", "$1", $body);
                    // fix tags
                    $array['body'] = trim($body);

                    // get the slugline
                    preg_match("'<xhtml:p prism:class=\"deck\">(.*?)</xhtml:p>'s", $ar_xml, $coincidencias);
                    if (isset($coincidencias[1])) {
                      $array['slugline'] = trim(strip_tags($coincidencias[1]));
                    } else {
                      $array['slugline'] = '';
                    }

                    // get the byline
                    preg_match("'<xhtml:p prism:class=\"byline\">(.*?)</xhtml:b>'s", $ar_xml, $coincidencias);
                    if (isset($coincidencias[1])) {
                      $temp = preg_replace("/<xhtml:br \\/>/", " ", $coincidencias[1]);
                      $temp = trim(strip_tags($temp));
                      $temp = preg_replace("/^by\s*/i", "", $temp);
                      $array['byline'] = ucwords(strtolower($temp));
                    } else {
                      $array['byline'] = '';
                    }

                    // get the pull quote
                    preg_match("'<xhtml:p prism:class=\"pullQuote\">(.*?)</xhtml:b>'s", $ar_xml, $coincidencias);
                    if (isset($coincidencias[1])) {
                      $array['pulled_quote'] = trim(ucwords(strtolower(strip_tags($coincidencias[1]))));
                    } else {
                      $array['pulled_quote'] = '';
                    }

                    // echo $ar_xml;

                    /* Images */
                    $images = array();
                    preg_match_all("'<pam:media>(.*?)</pam:media>'s", $ar_xml, $coincidencias);
                    // loop over matches and extract data
                    if (! empty($coincidencias[1])) {
                      $matches = $coincidencias[1];
                      foreach ($matches as $item) {
                        preg_match("/<dc:format>([^<]+)/", $item, $imatches);
                        if (isset($imatches[1]) && $imatches[1] == 'image/jpg') {
                          preg_match("'<pam:mediaReference pam:refid=\"(.*)\" />'", $item, $arr);
                          if (isset($arr[1])) {
                            $iarray = array();
                            $iarray['image'] = $arr[1];
                            preg_match("'<pam:caption>(.*?)</pam:caption>'s", $item, $arr);
                            if (isset($arr[1])) {
                              $iarray['caption'] = trim(strip_tags($arr[1]));
                            } else {
                              $iarray['caption'] = '';
                            }
                            $images[] = $iarray;
                          }
                        }
                      }
                    }

                    // print_r ($array);
                    $pub_date = strtotime($array['pub_date']);

                    $node = array(
                      'title' => Encoding::toUTF8($array['title']),
                      'summary' => strip_tags(Encoding::toUTF8($array['description'])),
                      'body' => Encoding::toUTF8($array['body']),
                      $byline_field => substr(Encoding::toUTF8($array['byline']), 0, 255), // trim to field length
                      $subhead_field => Encoding::toUTF8($array['slugline']),
                      'field_date1' => $pub_date, // Laurel Outlook
                    );

                    $array = [];
                    if (count($images) > 0) {
                      foreach ($images as $image) {
                        $ipath = $extract_dir . 'img/' . $image['image'];
                        $array[] = [
                          'name' => $image['image'],
                          'path' => $ipath,
                          'caption' => Encoding::toUTF8($image['caption']),
                        ];
                      }
                      $node['images'] = $array;
                    }

                    // otherwise field is initiated and shows empty on node page
                    if (! empty($array['pulled_quote'])) {
                      $node['field_pulled_quote'] = $array['pulled_quote'];
                    }

                    //print_r($node);

                    $values['created'] = $pub_date;
                    etype_xml_importer_entity_create($node, $values);
                    // exit;
                    $i++;
                    // echo $i . ' ';
                  }
                }
              }
            }
          }
        }
      }
    }
    watchdog('etype_xml_importer', "eType XML Importer imported %num stories.", $variables = array('%num' => $i), $severity = WATCHDOG_NOTICE);
  }
}