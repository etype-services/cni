<?php

/**
 * @file
 * API documentation for Classified Ads module.
 */

/**
 * Allows modules to modify the list of expired ads and act on them.
 *
 * @param array $ads_bunch
 *   A uid-indexed array of ad nodes.
 *
 * @see \classified_notifications_classified_expire_alter()
 */
function hook_classified_expires_alter(array $ads_bunch) {

}

/**
 * Allow modules to modify notifications due to be sent.
 *
 * @param array $ads_bunch
 *   A uid-indexed array of ad nodes.
 * @param string $kind
 *   A notification kind, from the list in _classified_get_notify_kinds().
 *
 * @see \classified_notifications_classified_notify_alter()
 */
function hook_classified_notify_alter(array $ads_bunch, $kind) {

}

/**
 * Allow modules to modify the list of ads due to be purged.
 *
 * @param array $ads_bunch
 *   A uid-indexed array of ad nodes.
 *
 * @see \classified_notifications_classified_purge_alter()
 */
function hook_classified_purge_alter(array $ads_bunch) {
}
