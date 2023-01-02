<?php
    include_once "./database_connect.php";
    if (isset($_GET["id"])) {
        $id = $_GET['id'];
        // $data = $_POST['data'];
        $sql = "UPDATE `ip` SET `address` = 'N/A', `datetime` = CURRENT_TIMESTAMP WHERE `ip`.`id` = ".$id.";";
        mysqli_query($connect, $sql);
    } else {
        # code...
        echo 'invalid back door';
    }
    
?>
