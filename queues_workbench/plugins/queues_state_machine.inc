<?php

/**
 * @file
 * State Flow implementation of the State Machine class
 */

class QueuesStatesEntity extends StateFlowEntity {

  /**
   * On enter published Callback.
   *
   * @see StateFlowEntity::fire_event()
   */
  public function on_enter_published() {
    state_flow_entity_set_entity_saved('queues', $this->object->qid, $this->object);
    $this->object->status = TRUE;
    $this->object->published_revision_id = $this->object->vid;
    if ($this->object->is_new === TRUE && isset($this->object->qid)) {
      $this->object->is_new = FALSE;
    }
    $this->object->save();
  }

  /**
   * On exit publish Callback.
   *
   * @see StateFlowEntity::fire_event()
   */
  public function on_enter_unpublished() {
    $this->object->status = FALSE;
    drupal_write_record('queues', $this->object, array('qid'));
    drupal_write_record('queues_revision', $this->object, array('vid'));
  }

  /**
   * On exit publish Callback.
   *
   * @see StateFlowEntity::fire_event()
   */
  public function on_exit_published() {
    // Do not do anything. Since onEnterUnpublished will do all the heavy
    // lifting.
  }

  /**
   * Set Published Callback.
   *
   * StateFlowEntity calls this directly so I can't use the camelCase.
   *
   * @see StateFlowEntity::fire_event()
   */
  public function set_published($reset = FALSE) {
    $this->object->status = TRUE;
    $this->object->published_revision_id = $this->object->vid;
    if (isset($this->object->is_new) && isset($this->object->qid)) {
      $this->object->is_new = FALSE;
    }
    $this->object->save();
  }
}
