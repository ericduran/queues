<?php

/**
 * @file
 * Profile type editing UI.
 */
class QueueEntityUIController extends EntityDefaultUIController {

 /**
  * Overrides hook_menu() defaults. We need to do this. The parent
  * class hook_menu() sucks for content management.
  */
  public function hook_menu() {
    $items = array();
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%entity_object';
    $plural_label = isset($this->entityInfo['plural label']) ? $this->entityInfo['plural label'] : $this->entityInfo['label'] . 's';

    // Lets get the default menu items.
    $items = parent::hook_menu();

    // We do not want a generic add queue page.
    unset($items[$this->path . '/add']);

    $items[$this->path] = array(
      'title' => $plural_label,
      'page callback' => 'drupal_get_form',
      'page arguments' => array($this->entityType . '_overview_form', $this->entityType),
      'description' => 'Manage ' . $plural_label . '.',
      'access callback' => 'entity_access',
      'access arguments' => array('view', $this->entityType),
      'file' => 'includes/entity.ui.inc',
      'type' => MENU_LOCAL_TASK,
    );

    $items[$this->path . '/list'] = array(
      'title' => 'List',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
    );

    // Add menu items to add each different type of entity.
    foreach (queues_type_get_types() as $type) {
      $items[$this->path . '/add/' . $type->type] = array(
        'title' => t('Add @queue', array('@queue' =>$type->label)),
        'page callback' => 'entity_ui_get_form',
        'page arguments' => array($this->entityType, NULL, 'add'),
        'access callback' => 'entity_access',
        'access arguments' => array('create', $this->entityType),
        'type' => MENU_LOCAL_ACTION,
      );
    }

    return $items;
  }

  public function hook_forms() {
    $forms = parent::hook_forms();

    if (!(count($this->entityInfo['bundles']) == 1 && isset($this->entityInfo['bundles'][$this->entityType]))) {
      foreach ($this->entityInfo['bundles'] as $bundle => $bundle_info) {
        $forms[$this->entityType . '_edit_' . $bundle . '_form']['callback'] = $this->entityType . '_form';
        // Again the wrapper callback is invoked by entity_ui_get_form() anyway.
      }
    }
    return $forms;
  }
}

function queues_form($form, $form_state, $QueueEntity, $op) {
  // TODO: Rename this form. This can clash with hook_form.

  if ($op == 'add') {
    // TODO: HacK!!! Time is of the essence, or is it?
    $bundle = arg(4);
    $QueueEntity->type = $bundle;
  }

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#required' => TRUE,
    '#default_value' => $QueueEntity->title,
    '#weight' => -10,
  );

  field_attach_form('queues', $QueueEntity, $form, $form_state);

  $form['actions'] = array(
    '#type' => 'actions'
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save queue'), // TODO: Save the "label" of the queue.
    '#weight' => 20,
  );

  return $form;
}

function queues_form_submit($form, &$form_state) {
  $QueueEntity = $form_state['queues'];
  entity_form_submit_build_entity('queues', $QueueEntity, $form, $form_state);
  $QueueEntity->save();
  $form_state['redirect'] = 'admin/content/queues';
}

