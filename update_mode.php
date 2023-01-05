<?php
    include_once "./database_connect.php";
    if (isset($_GET["mode"])) {
        $mode = $_GET["mode"];
        $sql = "UPDATE `robocar_datastream` SET `mode` = '".$mode."' WHERE `robocar_datastream`.`id` = 1;";
        mysqli_query($connect, $sql);
        echo "checkbox state updated!";
    } else {
        # code...
        echo 'invalid back door';
    }
?>    
