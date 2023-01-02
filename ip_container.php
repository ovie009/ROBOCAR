<?php
    include_once "./database_connect.php";
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
            $dateTime = strtotime($dateTime);
            $currentDateTime = date('Y-m-d G:i:s');
            $unixSeconds = date('U');
            $timeElapsed = $unixSeconds - $dateTime;

            // echo  $ipAddress;
            if ($ipAddress != "N/A") {
                if ($timeElapsed > 600) {
                    ?> <label for="ip_address">Camserver Ip address:</label>
                    <input type="text" name="ip_address" id="ip_address" value="<?php echo $ipAddress  ?>" placeholder="ip address of camserver" readonly>
                    <button class="esp_now_submit" type="submit">submit</button> 
                    <span  style="font-size: small;">Ip address has been saved in the server for over 10 mins</span><?php
                    # code...
                } else {
                    # code...
                    ?> <label for="ip_address">Camserver Ip address:</label>
                    <input type="text" name="ip_address" id="ip_address" value="<?php echo $ipAddress  ?>" placeholder="ip address of camserver" readonly>
                    <button class="esp_now_submit" type="submit">submit</button> 
                    <span  style="font-size: small;">Recent Ip Address detected</span><?php
                }
            } else {
                ?> <label for="ip_address">Camserver Ip address:</label>
                <input type="text" name="ip_address" id="ip_address" value="<?php echo $ipAddress; ?>" placeholder="ip address of camserver" readonly>
                <button class="esp_now_submit" type="submit">submit</button> <?php
            }
        }
    }
?>
