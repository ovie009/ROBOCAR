<?php
    include_once "./database_connect.php";
    if (isset($_GET["id"])) {
        $id = $_GET['id'];
        // sql query

        $sql = "SELECT `tolerance` FROM `robocar_datastream` WHERE `id` = 1;";
    
        // run query
        $result = mysqli_query($connect, $sql);
    
        while ($row = mysqli_fetch_assoc($result)) {
            # code...
            $tolerance = $row['tolerance'];
            if ($tolerance == "LOW") {
                ?><option value="LOW" selected>low</option>
                <option value="AVERAGE">average</option>
                <option value="HIGH">high</option> <?php
            } else if ($tolerance == "AVERAGE") {
                ?><option value="LOW">low</option>
                <option value="AVERAGE" selected>average</option>
                <option value="HIGH">high</option> <?php
            } else if ($tolerance == "HIGH") {
                ?><option value="LOW">low</option>
                <option value="AVERAGE">average</option>
                <option value="HIGH" selected>high</option> <?php
            }
        }
        
    } else {
        # code...
        echo 'invalid back door';
    }
?>    
