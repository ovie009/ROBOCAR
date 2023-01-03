<?php
    include_once "./database_connect.php";
    if (isset($_GET["IP"])) {
        $id = 1;
        $IP = $_GET['IP'];

        $sql = "UPDATE `ip` SET `address` = '".$IP."', `datetime` = CURRENT_TIMESTAMP WHERE `ip`.`id` = ".$id.";";
        mysqli_query($connect, $sql);

        // sql query
        $sql = "SELECT * FROM `robocar_datastream` WHERE id = ?;";
    
        // create prepared statement
        $stmt = mysqli_stmt_init($connect);
    
        // run prepared statement
        if (!mysqli_stmt_prepare($stmt, $sql)) {
            echo 'Query Failed';
        } else {
            // Bind parameters to the placeholder
            mysqli_stmt_bind_param($stmt, "s", $id);
            // run parameters inside database
            mysqli_stmt_execute($stmt);
            $result = mysqli_stmt_get_result($stmt);
            while ($row = mysqli_fetch_assoc($result)) {
                # code...
                $mode = $row['mode'];
                $flash = $row['flash'];
                $motionDetected = $row['motion_detected'];

                // echo $mode."#".$row."#".$motion_detected;
                echo $mode."#".$flash."&".$motionDetected;

            }
        }
    } else {
        # code...
        echo 'invalid back door';
    }
    
?>
