<?php

/**
 * @file
 * Expiration date field handler for Views.
 *
 * @copyright (c) 2010 Ouest Systemes Informatiques (OSInet)
 *
 * @license General Public License version 2 or later
 *
 * Original code, not derived from the ed_classified module.
 */

/**
 * Class classified_handler_field_date_purge is a views plugin.
 *
 * @ingroup views_field_handlers
 *
 * Naming is constrained for Views integration in D7, so disable naming
 * conventions.
 *
 * phpcs:disable Drupal.NamingConventions.ValidClassName,PSR1.Classes.ClassDeclaration,Squiz.Classes.ValidClassName
 */
class classified_handler_field_date_purge extends views_handler_field_date {

  /**
   * {@inheritDoc}
   */
  public function render($values) {

    $grace = _classified_get('grace');

    // Save expires.
    $expires = $values->classified_node_expires;

    // Compute purge.
    $values->classified_node_expires += $grace * 24 * 60 * 60;

    // Render purge.
    $ret = parent::render($values);

    // Restore expires.
    $values->classified_node_expires = $expires;
    return $ret;
  }

}
