var fs = require('fs');

var content = fs.readFileSync('../../input/03/input.txt', 'utf8');

var contentArr = content.split("\r\n");

var wire1 = contentArr[0].split(",");
var wire2 = contentArr[1].split(",");

var convertStrToPair = function(value, i, wire) {
    wire[i] = {
        direction: value.slice(0, 1),
        distance: parseInt(value.slice(1))
    };
};

wire1.forEach(convertStrToPair);
wire2.forEach(convertStrToPair);

var getIntersection = function(line1, line2) {
    if((line1.x1 === line1.x2) === (line2.x1 === line2.x2)) {
        return false;
    }
    var vertical = (line1.x1 === line1.x2) ? line1 : line2;
    var horizontal = (line1.x1 === line1.x2) ? line2 : line1;
    if(
        ((vertical.x1 >= horizontal.x1 && vertical.x1 <= horizontal.x2) ||
        (vertical.x1 <= horizontal.x1 && vertical.x1 >= horizontal.x2))
        &&
        ((horizontal.y1 >= vertical.y1 && horizontal.y1 <= vertical.y2) ||
        (horizontal.y1 <= vertical.y1 && horizontal.y1 >= vertical.y2))
    ) {
        return {x: vertical.x1, y: horizontal.y1};
    }
    return false;
};

var prepareCurrentLine = function (currentLine, wireElement) {
    currentLine.x1 = currentLine.x2;
    currentLine.y1 = currentLine.y2;
    switch (wireElement.direction) {
        case "R":
            currentLine.x2 += wireElement.distance;
            break;
        case "U":
            currentLine.y2 += wireElement.distance;
            break;
        case "L":
            currentLine.x2 -= wireElement.distance;
            break;
        case "D":
            currentLine.y2 -= wireElement.distance;
            break;
        default:
            console.warn("unexpected direction '" + wireElement.direction + "'");
    }
};

var lowestDistance = null;
var currentLine1 = {x1: 0, y1: 0, x2: 0, y2: 0};
for (var i = 0; i < wire1.length; i++) {
    prepareCurrentLine(currentLine1, wire1[i]);
    var currentLine2 = {x1: 0, y1: 0, x2: 0, y2: 0};
    for (var j = 0; j < wire2.length; j++) {
        prepareCurrentLine(currentLine2, wire2[j]);
        var intersection = getIntersection(currentLine1, currentLine2);
        if(intersection !== false) {
            var distance = (intersection.x < 0) ? intersection.x * -1 : intersection.x;
            distance += (intersection.y < 0) ? intersection.y * -1 : intersection.y;
            if(!lowestDistance || distance < lowestDistance) {
                lowestDistance = distance;
            }
        }
    }
}

console.log("The distance to the closest intersection is: " + lowestDistance);