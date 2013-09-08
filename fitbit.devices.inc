<?php

/**
* @file
* Support for device-related calls
*/


require_once ('fitbit.module');

DEFINE ('FITBIT_DEVICE_ENDPOINT', '/user/-/devices.json');


/**
 *
 */
function fitbit_get_devices($uid, $client) {
  $url = FITBIT_BASEURL . FITBIT_APIVER . FITBIT_DEVICE_ENDPOINT;
  $response = $client->get($url);
  $response = json_decode(json_encode($response));

  return $response;
}
