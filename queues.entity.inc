<?php

/**
 * @file
 * Class API and helper for our queues entity.
 */

/**
 *
 */
class QueueEntity extends Entity {
  public $title;
  public $type;
  public $description;
  public $is_new = FALSE;

  public function __construct($values = array()) {
    parent::__construct($values, 'queues');
  }

  protected function defaultLabel() {
    return $this->title;
  }


  public function save() {
    parent::save();
  }

  protected function defaultUri() {
    // Queues have no display. Only a management screen.
    return array('path' => 'admin/content/queues/manage/' . $this->identifier());
  }
}

/**
 * Load multiple models based on certain conditions.
 *
 * @param $queues_ids
 *   An array of queue IDs.
 * @param $conditions
 *   An array of conditions to match against the {queues} table.
 * @param $reset
 *   A boolean indicating that the internal cache should be reset.
 * @return
 *   An array of queue objects, indexed by queue_id.
 *
 * @see entity_load()
 * @see queue_load()
 */
function queue_load_multiple($queues_ids = array(), $conditions = array(), $reset = FALSE) {
  return entity_load('queues', $queues_ids, $conditions, $reset);
}
