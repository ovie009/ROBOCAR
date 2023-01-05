<?php
    include_once "./database_connect.php";
    if (isset($_GET["tolerance"])) {
        $tolerance = $_GET["tolerance"];
        $sql = "UPDATE `robocar_datastream` SET `tolerance` = '".$tolerance."' WHERE `robocar_datastream`.`id` = 1;";
        mysqli_query($connect, $sql);
        echo "checkbox state updated!";
    } else {
        # code...
        echo 'invalid back door';
    }
?>    
