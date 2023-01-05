<?php
    include_once "./database_connect.php";
    if (isset($_GET["id"])) {
        $id = $_GET['id'];
        // sql query

        $sql = "SELECT `mode` FROM `robocar_datastream` WHERE `id` = 1;";
    
        // run query
        $result = mysqli_query($connect, $sql);
    
        while ($row = mysqli_fetch_assoc($result)) {
            # code...
            $mode = $row['mode'];

            if ($mode == "STREAM") {
                ?><option value="STREAM" selected>stream</option>
                <option value="CAPTURE">capture</option> <?php
            } else if ($mode == "CAPTURE") {
                ?><option value="STREAM">stream</option>
                <option value="CAPTURE" selected >capture</option><?php
            }
        }
        
    } else {
        # code...
        echo 'invalid back door';
    }
?>    
