<?php
    include_once "./database_connect.php";        
    
    $mode = "STREAM";
    $sql = "UPDATE `robocar_datastream` SET `mode` = '".$mode."' WHERE `robocar_datastream`.`id` = 1;";
    mysqli_query($connect, $sql);
    $expiration = time() + 7200; // expiration date is two hours from now
    setcookie("mode", $mode, $expiration);

    $id = 1;
    // sql query
    $sql = "SELECT * FROM `ip` WHERE id = ?;";

    // create prepared statement
    $stmt = mysqli_stmt_init($connect);

    // run prepared statement
    if (!mysqli_stmt_prepare($stmt, $sql)) {
        // echo 'Query Failed';
    } else {
        // Bind parameters to the placeholder
        mysqli_stmt_bind_param($stmt, "s", $id);
        // run parameters inside database
        mysqli_stmt_execute($stmt);
        $result = mysqli_stmt_get_result($stmt);
        while ($row = mysqli_fetch_assoc($result)) {
            # code...
            $ipAddress = $row['address'];
            $dateTime = $row['datetime'];
            $dateTime = strtotime($dateTime) + 3600;
            $currentDateTime = date('Y-m-d G:i:s');
            $unixSeconds = date('U');
            $timeElapsed = $unixSeconds - $dateTime;

            // echo  $ipAddress;
            if ($ipAddress == "N/A") {
                ?> <em style="font-size: small;" class="esp_failed">ESP NOW CONNECTION FAILED: recommend reseting both esp modules</em> <?php
            } else {
                ?> <p class="esp_now_footer_text" style="font-size: small;"> Run ngrok app, type <em>"ngrok http <?php echo $ipAddress; ?> "</em> <button id="copy-button" class="copy-button" type="button">copy</button> the resulting ngrok port forward address and paste in in the input field. Also paste the address in your browser and click on visit
                </p><?php
            }
        }
    }
?>
