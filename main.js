$(document).ready(function() {

    $(".car-buttons").click(function() {

        let direction = this.id; // get the id of the button
        // the id of the button is equal to the direction of the button
        $.post("updateDb.php", {
            car: direction
        })

        console.log(this.id)
    })

    $(".reset-camera").click(function() {
        let direction = 'center'; // get the id of the button
        // the id of the button is equal to the direction of the button
        $.post("updateDb.php", {
            camera: direction
        })
    })

})