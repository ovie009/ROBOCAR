<?php
    include_once "./database_connect.php";
    if (isset($_GET["id"])) {
        $id = $_GET['id'];
        // sql query

        $sql = "SELECT `flash` FROM `robocar_datastream` WHERE `id` = 1;";
    
        // run query
        $result = mysqli_query($connect, $sql);
    
        while ($row = mysqli_fetch_assoc($result)) {
            # code...
            $flash = $row['flash'];
            echo $flash;
        }
        
    } else {
        # code...
        echo 'invalid back door';
    }
?>    
