<?php


/**
 * Export last 10 published nodes from site to concatenation db
 */
function etype_wire_node_export() {

  /*select *
from node n
join field_data_field_section f
on n.nid = f.entity_id
join taxonomy_term_data t
on f.field_section_tid = t.tid
where t.name REGEXP "free";
  */
    /* get last 10 published nodes from this site */
  $query = db_select('node', 'n');
  $query->join('field_data_field_section', 'f', 'n.nid = f.entity_id');
  $query->join('taxonomy_term_data', 't', 'f.field_section_tid = t.tid');
  $db_or = db_or();
  $db_or->condition('t.name', 'news','REGEXP');
  $db_or->condition('t.name', 'sports','REGEXP');
  $db_or->condition('t.name', 'free','REGEXP');
  $query->fields('n');
  $query->condition('n.type', 'article');
  $query->condition('n.status', '1');
  $query->condition($db_or);
  $query->orderBy('n.created', 'DESC');
  $query->range(0, 10);
  $results = $query->execute();

  print($query);
  dpm($query->arguments());

    $nodes = array();
    while ($n = $results->fetchAssoc()) {
        $nodes[] = $n;
    }

    if (count($nodes) > 0) {

        $dbHandle = _etype_wire_connect();

        global $base_url;
        $site_name = variable_get('site_name', 'Drupal');
        $etype_wire_cluster = variable_get('etype_wire_cluster');

        /* barf if cluster is not set up */
        if (empty($etype_wire_cluster)) {
            return;
        }
        $cluster = implode($etype_wire_cluster, ',');

        /* Delete old nodes */
        $sql = "DELETE FROM node WHERE `site` = '$base_url'";
        $stmt = $dbHandle->prepare($sql);
        $stmt->execute();

        foreach ($nodes as $node) {
            $object = node_load($node['nid']);
            $wrapper = entity_metadata_wrapper('node', $object);

            $body = $wrapper->body->value();
            $safe_body = _etype_clean_string($body['safe_value']);

            if (isset ($wrapper->field_kicker)) {
                $kicker = $wrapper->field_kicker->value();
            }
            else {
                $kicker = '';
            }
            $safe_kicker = strip_tags($kicker['safe_value']);

            // var_dump($wrapper);
            // echo "\n\n\n\n";

            $image_uri = isset($wrapper->field_image[0]->value()['uri']) ? $wrapper->field_image[0]->value()['uri'] : '';
            if (!empty($image_uri)) {
                // create real url
                $file_path = file_create_url($image_uri);
                // get caption
                $caption = isset($wrapper->field_image[0]->value()['image_field_caption']['value']) ? $wrapper->field_image[0]->value()['image_field_caption']['value'] : '';
                $safe_caption = strip_tags($caption);
            } else {
                $file_path = '';
                $safe_caption = '';
            }

            $sql = "INSERT INTO node (
`nid`, `vid`, `type`, `language`, `title`, `body`, `file`, `kicker`, `caption`, `uid`, `status`, `created`, `changed`, `comment`, `promote`, `sticky`, `tnid`, `translate`, `uuid`, `site`, `site_name`, `cluster`) 
VALUES (
    '" . $node['nid'] . "',
    '" . $node['vid'] . "',
     'article',
     '" . $node['language'] . "',
      '" . $node['title'] . "',
       '" . $safe_body . "',
        '" . $file_path . "',
         '" . $safe_kicker . "',
          '" . $safe_caption . "',
           '" . $node['uid'] . "',
            '0',
             '" . $node['created'] . "',
              '" . $node['changed'] . "',
               '" . $node['comment'] . "',
                '0',
                 '0',
                  '" . $node['tnid'] . "',
                   '" . $node['translate'] . "',
                    '" . $node['uuid'] . "',
                     ?,
                      ?,
                       ?)";
            $stmt = $dbHandle->prepare($sql);
            try {
                $stmt->execute(["$base_url", "$site_name","$cluster"]);
            } catch (Exception $e) {
                echo "There was an error inserting the data";
            }
        }

    }

}