<?php

/**
 * @file
 * State Flow implementation of the State Machine class
 */

class QueuesStatesEntity extends StateFlowEntity {

  public function on_enter_published() {
    state_flow_entity_set_entity_saved('queues', $this->object->qid, $this->object);
    $this->object->status = TRUE;
    $this->object->published_revision_id = $this->object->vid;
    $this->object->save();
  }

  public function on_exit_published() {
    $this->object->status = FALSE;
    $this->object->save();
  }
}
