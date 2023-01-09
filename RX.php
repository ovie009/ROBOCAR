<?php
    include_once "./database_connect.php";
    if (isset($_GET["id"])) {
        $id = $_GET['id'];
        $motion = $_GET['motion'];
        // sql query
        $sql = "SELECT `data`, `datetime`, `mode` FROM `robocar_datastream` WHERE `id` = 1;";
    
        // run query
        $result = mysqli_query($connect, $sql);
    
        while ($row = mysqli_fetch_assoc($result)) {
            # code...
            $data = $row['data'];
            $dateTime = $row['datetime'];
            $mode = $row['mode'];
            $dateTime = strtotime($dateTime) + 3600;
            $unixSeconds = date('U');
            $time = time();
            
            $timeElapsed = $unixSeconds - $dateTime;
            // echo  'dateTime: '.$dateTime;
            // echo '<br>';
            // echo 'unixSeconds: '.$unixSeconds;
            // echo '<br>';
            // echo  'time: '.$time;
            // echo '<br>';
            // echo 'timeElasped: '.$timeElapsed;
            // echo '<br>';
            // echo 'mode: '.$mode;
            // echo '<br>';
            // echo 'data: '.$data;
            // echo '<br>';
            // amount of seconds to elapse to disregard input 
            if ($timeElapsed > 5) {
                echo 'N/A#'.$mode;
            } else {
                echo $data.'#'.$mode;
            }
        }
        
        $sql = "UPDATE `robocar_datastream` SET `motion_detected` = '".$motion."' WHERE `robocar_datastream`.`id` = 1;";
        mysqli_query($connect, $sql);
    } else {
        # code...
        echo 'invalid back door';
    }
?>    
