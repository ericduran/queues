<?php

namespace Drupal\Queues\tests\units;

require_once '../mageekguy.atoum.phar';

include '../../queues.helpers.inc';

use \mageekguy\atoum;
use \Drupal\Queues;

class QueuesHelpers extends atoum\test {

  public function testFieldName() {
    $field_name_1 = "my_really_long_field_name_value";
    $field_name_2 = "my_short_field_name";
    $field_name_3 = "my_extremely_long_field_name_value_extra_long";

    $QueuesHelpers = new Queues\QueuesHelpers();

    $this->string($QueuesHelpers->get_target_field_name($field_name_1))->hasLengthLessThan(33);
    $this->string($QueuesHelpers->get_target_field_name($field_name_2))->hasLengthLessThan(33);
    $this->string($QueuesHelpers->get_target_field_name($field_name_3))->hasLengthLessThan(33);
  }
}
