<?php

  /* funzione che seleziona dal database l'ultimo elemento iuserito e lo impacchetta in formato json */

  function getUID() {
    $myObj = new \stdClass;
    include ("connect.php");

    $uid_log = null;
    $call_log = null;
    $log = null;

    $log = "SELECT * FROM log ORDER BY time DESC LIMIT 1";
    $call_log = $conn->query($log);
    while ($row = $call_log->fetch_assoc()){
      $uid_log = $row['uid'];
      $time_log = $row['time'];
    };

    $myObj->log_uid = $uid_log;
    $myObj->log_time = $time_log;


    header('Access-Control-Allow-Origin: local/host/fafi-card');
    header('Content-Type: application/json');
    echo json_encode($myObj);

  };

  getUID();


?>
