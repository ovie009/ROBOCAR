<?php
    include_once "./database_connect.php";

    // $_POST['id']
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
            echo $row['car'];
            echo '<br>';
            echo $row['camera'];
        }
        echo 'here';
    }
?>