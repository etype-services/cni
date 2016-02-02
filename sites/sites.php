<?php

/**
 * @file
 * Configuration file for Drupal's multi-site directory aliasing feature.
 *
 * Drupal searches for an appropriate configuration directory based on the
 * website's hostname and pathname. A detailed description of the rules for
 * discovering the configuration directory can be found in the comment
 * documentation in 'sites/default/default.settings.php'.
 *
 * This file allows you to define a set of aliases that map hostnames and
 * pathnames to configuration directories. These aliases are loaded prior to
 * scanning for directories, and they are exempt from the normal discovery
 * rules. The aliases are defined in an associative array named $sites, which
 * should look similar to the following:
 *
 * $sites = array(
 *   'devexample.com' => 'example.com',
 *   'localhost.example' => 'example.com',
 * );
 *
 * The above array will cause Drupal to look for a directory named
 * "example.com" in the sites directory whenever a request comes from
 * "example.com", "devexample.com", or "localhost/example". That is useful
 * on development servers, where the domain name may not be the same as the
 * domain of the live server. Since Drupal stores file paths into the database
 * (files, system table, etc.) this will ensure the paths are correct while
 * accessed on development servers.
 *
 * To use this file, copy and rename it such that its path plus filename is
 * 'sites/sites.php'. If you don't need to use multi-site directory aliasing,
 * then you can safely ignore this file, and Drupal will ignore it too.
 */

/**
 * Multi-site directory aliasing:
 *
 * Edit the lines below to define directory aliases. Remove the leading hash
 * signs to enable.
 */

$sites['whitecountynews.etypegoogle3.com'] = 'whitecountynews.net';
$sites['whitecountynews.net'] = 'whitecountynews.net';
$sites['www.whitecountynews.net'] = 'whitecountynews.net';
$sites['prod.whitecountynews.net'] = 'whitecountynews.net';
$sites['dev.whitecountynews.net'] = 'whitecountynews.net';

$sites['tribune-georgian.etypegoogle3.com'] = 'tribune-georgian.com';
$sites['tribune-georgian.com'] = 'tribune-georgian.com';
$sites['www.tribune-georgian.com'] = 'tribune-georgian.com';
$sites['prod.tribune-georgian.com'] = 'tribune-georgian.com';
$sites['dev.tribune-georgian.com'] = 'tribune-georgian.com';

$sites['thetoccoarecord.etypegoogle3.com'] = 'thetoccoarecord.com';
$sites['thetoccoarecord.com'] = 'thetoccoarecord.com';
$sites['www.thetoccoarecord.com'] = 'thetoccoarecord.com';
$sites['prod.thetoccoarecord.com'] = 'thetoccoarecord.com';
$sites['dev.thetoccoarecord.com'] = 'thetoccoarecord.com';

$sites['thenortheastgeorgian.etypegoogle3.com'] = 'thenortheastgeorgian.com';
$sites['thenortheastgeorgian.com'] = 'thenortheastgeorgian.com';
$sites['www.thenortheastgeorgian.com'] = 'thenortheastgeorgian.com';
$sites['prod.thenortheastgeorgian.com'] = 'thenortheastgeorgian.com';
$sites['dev.thenortheastgeorgian.com'] = 'thenortheastgeorgian.com';

$sites['myandrewsjournal.etypegoogle3.com'] = 'myandrewsjournal.com';
$sites['myandrewsjournal.com'] = 'myandrewsjournal.com';
$sites['www.myandrewsjournal.com'] = 'myandrewsjournal.com';
$sites['prod.myandrewsjournal.com'] = 'myandrewsjournal.com';
$sites['dev.myandrewsjournal.com'] = 'myandrewsjournal.com';

$sites['lakecityreporter.etypegoogle3.com'] = 'lakecityreporter.com';
$sites['lakecityreporter.com'] = 'lakecityreporter.com';
$sites['www.lakecityreporter.com'] = 'lakecityreporter.com';
$sites['prod.lakecityreporter.com'] = 'lakecityreporter.com';
$sites['dev.lakecityreporter.com'] = 'lakecityreporter.com';

$sites['thehartwellsun.etypegoogle3.com'] = 'thehartwellsun.com';
$sites['thehartwellsun.com'] = 'thehartwellsun.com';
$sites['www.thehartwellsun.com'] = 'thehartwellsun.com';
$sites['prod.thehartwellsun.com'] = 'thehartwellsun.com';
$sites['dev.thehartwellsun.com'] = 'thehartwellsun.com';
 
$sites['franklincountycitizen.etypegoogle3.com'] = 'franklincountycitizen.com';
$sites['franklincountycitizen.com'] = 'franklincountycitizen.com';
$sites['www.franklincountycitizen.com'] = 'franklincountycitizen.com';
$sites['prod.franklincountycitizen.com'] = 'franklincountycitizen.com';
$sites['dev.franklincountycitizen.com'] = 'franklincountycitizen.com';

$sites['fbnewsleader.etypegoogle3.com'] = 'fbnewsleader.com';
$sites['fbnewsleader.com'] = 'fbnewsleader.com';
$sites['www.fbnewsleader.com'] = 'fbnewsleader.com';
$sites['prod.fbnewsleader.com'] = 'fbnewsleader.com';
$sites['dev.fbnewsleader.com'] = 'fbnewsleader.com';

$sites['elberton.etypegoogle3.com'] = 'elberton.com';
$sites['elberton.com'] = 'elberton.com';
$sites['www.elberton.com'] = 'elberton.com';
$sites['prod.elberton.com'] = 'elberton.com';
$sites['dev.elberton.com'] = 'elberton.com';

$sites['thedahloneganugget.etypegoogle3.com'] = 'thedahloneganugget.com';
$sites['thedahloneganugget.com'] = 'thedahloneganugget.com';
$sites['www.thedahloneganugget.com'] = 'thedahloneganugget.com';
$sites['prod.thedahloneganugget.com'] = 'thedahloneganugget.com';
$sites['dev.thedahloneganugget.com'] = 'thedahloneganugget.com';

$sites['theclaytontribune.etypegoogle3.com'] = 'theclaytontribune.com';
$sites['theclaytontribune.com'] = 'theclaytontribune.com';
$sites['www.theclaytontribune.com'] = 'theclaytontribune.com';
$sites['prod.theclaytontribune.com'] = 'theclaytontribune.com';
$sites['dev.theclaytontribune.com'] = 'theclaytontribune.com';

$sites['cherokeescout.etypegoogle3.com'] = 'cherokeescout.com';
$sites['cherokeescout.com'] = 'cherokeescout.com';
$sites['www.cherokeescout.com'] = 'cherokeescout.com';
$sites['prod.cherokeescout.com'] = 'cherokeescout.com';
$sites['dev.cherokeescout.com'] = 'cherokeescout.com';

$sites['beachesleader.etypegoogle3.com'] = 'beachesleader.com';
$sites['beachesleader.com'] = 'beachesleader.com';
$sites['www.beachesleader.com'] = 'beachesleader.com';
$sites['prod.beachesleader.com'] = 'beachesleader.com';
$sites['dev.beachesleader.com'] = 'beachesleader.com';
 
$sites['thenewsobserver.etypegoogle3.com'] = 'thenewsobserver.com';
$sites['thenewsobserver.com'] = 'thenewsobserver.com';
$sites['www.thenewsobserver.com'] = 'thenewsobserver.com';
$sites['prod.thenewsobserver.com'] = 'thenewsobserver.com';
$sites['dev.thenewsobserver.com'] = 'thenewsobserver.com';

$sites['claycountyprogress.etypegoogle3.com'] = 'claycountyprogress.com';
$sites['claycountyprogress.com'] = 'claycountyprogress.com';
$sites['www.claycountyprogress.com'] = 'claycountyprogress.com';
$sites['prod.claycountyprogress.com'] = 'claycountyprogress.com';
$sites['dev.claycountyprogress.com'] = 'claycountyprogress.com';

$sites['timescourier.etypegoogle3.com'] = 'timescourier.com';
$sites['timescourier.com'] = 'timescourier.com';
$sites['www.timescourier.com'] = 'timescourier.com';
$sites['prod.timescourier.com'] = 'timescourier.com';
$sites['dev.timescourier.com'] = 'timescourier.com';
