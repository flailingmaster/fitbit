<?php

/**
* @file
* Admin functions
*/

require_once ('fitbit.devices.inc');

/**
 * Implements hook_admin()
 */
function fitbit_admin($form, &$form_state) {
  $form = array();

  $form['fitbit_intro'] = array(
    '#type' => 'markup',
    '#markup' => t('You must first register an app with Fitbit here: https://dev.fitbit.com/apps/new'),
  );

  $form['fitbit_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Consumer key'),
    '#default_value' => variable_get('fitbit_key'),
    '#size' => 50,
    '#required' => TRUE,
  );

  $form['fitbit_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Consumer secret'),
    '#default_value' => variable_get('fitbit_secret'), '#size' => 50,
    '#required' => TRUE,
  );

  return system_settings_form($form);
}


/**
 * A page to submit tests to the Fitbit API
 */
function fitbit_admin_tester($form, &$form_state) {
  global $user;
  $form = array();

  $key = variable_get('fitbit_key');

  if ($client = fitbit_get_access_client($user->uid)) {
    $devices = fitbit_get_devices($user->uid, $client);

    
    return $form;
  }

  drupal_set_message(t('You have not connected your account to the Fitbit API yet.'), 'error');

  $form['account_link'] = array(
    '#type' => 'link',
    '#title' => t('Edit your account'),
    '#href' => 'user/' . $user->uid . '/edit',
  );

  return $form;
}