<?php
    include_once "./database_connect.php";
    if (isset($_GET["frame"])) {
        $frame = $_GET["frame"];
        $sql = "UPDATE `robocar_datastream` SET `frame` = '".$frame."' WHERE `robocar_datastream`.`id` = 1;";
        mysqli_query($connect, $sql);
        echo "checkbox state updated!";
    } else {
        # code...
        echo 'invalid back door';
    }
?>    
