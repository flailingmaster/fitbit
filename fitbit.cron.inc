<?php

/**
* @file
* Cron-related functions
*/


/**
 * Implements hook_cron_queue_info()
 */
function fitbit_cron_queue_info() {
  $queues = array();

  $queues['fitbit_badges_queue'] = array(
    'worker callback' => 'fitbit_sync_badges',
    'time' => 60,
  );

  $queues['fitbit_weights_queue'] = array(
    'worker callback' => 'fitbit_sync_weights',
    'time' => 60,
  );

  $queues['fitbit_steps_queue'] = array(
    'worker callback' => 'fitbit_sync_steps',
    'time' => 60,
  );

  return $queues;
}


function fitbit_cron() {
  $fitbit_users = fitbit_get_connected_users();

  $badges_queue = DrupalQueue::get('fitbit_badges_queue');
  $weights_queue = DrupalQueue::get('fitbit_weights_queue');
  $steps_queue = DrupalQueue::get('fitbit_steps_queue');

  foreach ($fitbit_users as $account) {
    if(isset($account->uid)) {
      $badges_queue->createItem($account->uid);
      $weights_queue->createItem($account->uid);
      $steps_queue->createItem($account->uid);
    }
  }
}
