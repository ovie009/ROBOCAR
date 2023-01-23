<?php
    include_once "./database_connect.php";

    $sql = "SELECT `datetime` FROM `ip` WHERE `id` = 1;";
    $result = mysqli_query($connect, $sql);
    while ($row = mysqli_fetch_assoc($result)) {
        $dateTime = $row['datetime'];
        $dateTime = strtotime($dateTime) + 3600;
        // $dateTime = strtotime($dateTime);
        $currentDateTime = date('Y-m-d G:i:s');
        $unixSeconds = date('U');
        $timeElapsed = $unixSeconds - $dateTime;

        if ($timeElapsed > 10) {
            # code...
            ?><span class="esp_disconnected">ESP32 CAM</span><?php
        } else {
            # code...
            ?><span class="esp_connected">ESP32 CAM</span><?php
        }
    }
    
    $sql = "SELECT `esp8266_timestamp` FROM `robocar_datastream` WHERE `id` = 1;";
    // run query
    $result = mysqli_query($connect, $sql);
    while ($row = mysqli_fetch_assoc($result)) {
        $timeStamp = $row['esp8266_timestamp'];
        //$timeStamp = strtotime($timeStamp) + 3600;
        $timeStamp = strtotime($timeStamp);
        $currentDateTime = date('Y-m-d G:i:s');
        $unixSeconds = date('U');
        $timeElapsed = $unixSeconds - $timeStamp;
        if ($timeElapsed > 10) {
            # code...
            ?><span class="esp_disconnected">ESP8266</span><?php
        } else {
            # code...
            ?><span class="esp_connected">ESP8266</span><?php
        }
    }
?>
