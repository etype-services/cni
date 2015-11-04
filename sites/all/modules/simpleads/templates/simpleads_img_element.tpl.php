<?php

/**
 * @file
 * SimpleAds Image ad.
<<<<<<< HEAD
 *
=======
 * 
>>>>>>> origin/master
 * Avaialable variables
 * array $ad
 * array $settings
 * array $image_attributes
 * array $link_attributes
<<<<<<< HEAD
 *
 */
?>
<div class="simplead-container image-ad <?php if (isset($css_attributes)): print $css_attributes; endif; ?>">
  <?php if (!empty($ad['destination_url'])) : ?>
    <?php print l(theme('image', $image_attributes), $ad['url'], $link_attributes); ?>
  <?php else : ?>
    <?php print theme('image', $image_attributes); ?>
  <?php endif; ?>
=======
 * 
 */
?>
<div class="simplead-container image-ad <?php if (isset($css_attributes)): print $css_attributes; endif; ?>">
  <?php print l(theme('image', $image_attributes), $ad['url'], $link_attributes); ?>
>>>>>>> origin/master
</div>