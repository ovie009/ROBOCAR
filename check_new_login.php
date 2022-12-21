<?php
    // echo "newLogin";
    session_start();
    include_once "./database_connect.php";
    if (isset($_POST["id"])) {
        $id = 1;
        // sql query
        $sql = "SELECT * FROM `login` WHERE id = ?;";
    
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
                $loginLastTimestamp = $row['datetime'];
                $savedTimeStamp = $_SESSION['login_timestamp'];
                if (strtotime($loginLastTimestamp) > strtotime($savedTimeStamp)) {
                    # code...
                    session_unset();
                    session_destroy();
                    echo "new user found!";
                } else {
                    # code...
                    echo "same user!";
                }
                
            }
            mysqli_stmt_close($stmt);
            mysqli_close($connect);
        }
    }
?>