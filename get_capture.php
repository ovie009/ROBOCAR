<?php
    include_once "./database_connect.php";
    if (isset($_GET["id"])) {
        $id = $_GET['id'];
        // sql query

        $sql = "SELECT `data`, `mode` FROM `robocar_datastream` WHERE `id` = 1;";
    
        // run query
        $result = mysqli_query($connect, $sql);
    
        while ($row = mysqli_fetch_assoc($result)) {
            # code...
            $data = $row['data'];
            $mode = $row['mode'];

            if ($data == "captured_image" && $mode == "CAPTURE") {
                ?><div class="captured_image_container">
                    Image captured click <em><a href="./capture.php">here</a></em> to view image  
                </div><?php
            } else {
                echo '';
            }
        }
        
    } else {
        # code...
        echo 'invalid back door';
    }
?>    
