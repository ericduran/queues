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
    if (strlen($entity_type) <= 23) {
      return 'field_qt_' . $entity_type;
    }
    else {
      // Field names cannot be longer than 32 characters, so have to use a hashing
      // trick in order to get a human-readable field name for long entity types.
      return 'field_qt_' . substr($entity_type, 0, 15) . '_' . substr(md5($entity_type), 0, 7);
    }
  }
}
