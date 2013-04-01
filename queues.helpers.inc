<?php

/**
 * @file
 *
 * Helper functions for Queues.
 *
 * Seperating them out for simpler unit test.
 */

namespace Drupal\Queues;

class QueuesHelpers {

  /**
   * Helper function for getting the name of a entityreference field.
   *
   * @param string $entity_type
   *   A Drupal entity type.
   *
   * @return string
   *   The name of the entityreference field for the given entity type.
   */
  public function get_target_field_name($entity_type) {
    if (drupal_strlen($entity_type) <= 23) {
      return 'field_qt_' . $entity_type;
    }
    else {
      // Field names cannot be longer than 32 characters, so have to use a hashing
      // trick in order to get a human-readable field name for long entity types.
      return 'field_qt_' . substr($entity_type, 0, 15) . '_' . substr(md5($entity_type), 0, 7);
    }
  }
}


/**
 * Hack to work around missing drupal_strlen.
 * :-/
 */
if (!function_exists('drupal_strlen')) {
  if (UNICODE_MULTIBYTE) {
    define('UNICODE_MULTIBYTE', 1);
  }

  function drupal_strlen($text) {
    global $multibyte;
    if ($multibyte == UNICODE_MULTIBYTE) {
      return mb_strlen($text);
    }
    else {
      // Do not count UTF-8 continuation bytes.
      return strlen(preg_replace("/[\x80-\xBF]/", '', $text));
    }
  }
}
