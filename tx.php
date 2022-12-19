<?php
    include_once "./database_connect.php";
    if (isset($_POST["id"])) {
        $id = $_POST['id'];
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
                $data = $row['data'];
                $dateTime = $row['datetime'];
                $dateTime = strtotime($dateTime);
                $currentDateTime = date('Y-m-d G:i:s');
                $unixSeconds = date('U');
                $timeElapsed = $unixSeconds - $dateTime;
                if ($timeElapsed > 10) {
                    echo 'N/A';
                } else {
                    echo $data;
                }
            }
        }
    } else {
        # code...
        echo 'invalid back door';
    }
    
?>
