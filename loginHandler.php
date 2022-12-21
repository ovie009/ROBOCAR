<?php

    include_once "./database_connect.php";
    if (isset($_POST["user"])) {
        $user = $_POST['user'];
        $password = $_POST['password'];

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
                $dataUser = $row['user'];
                $dataPassword = $row['password'];
                if ($user === $dataUser) {
                    # code...
                    if ($password === $dataPassword) {
                        # code...
                        session_start();
                        $dateTime = date("Y-m-d G:i:s");
                        $_SESSION['user'] = $dataUser;
                        $_SESSION['login_timestamp'] = $dateTime;
                        $sql = "UPDATE `login` SET `datetime` = '".$dateTime."' WHERE `login`.`id` = 1;";
                        mysqli_query($connect, $sql);
                        echo "successful";
                        header("location: index.php?successful");
                        
                    } else {
                        header("location: index.php?incorrectPassword");
                    }
                } else {
                    header("location: index.php?invalidUsername");
                }
            }
            mysqli_stmt_close($stmt);
            mysqli_close($connect);
        }
    } else {
        # code...
        echo 'invalid back door';
    }
    
?>
