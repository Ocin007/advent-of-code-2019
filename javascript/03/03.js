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

//part 1
var part1 = function () {
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
};

var getStepsForLine = function (currentLine, intersection) {
    var steps;
    if(currentLine.x1 === currentLine.x2) {
        steps = currentLine.y1 - intersection.y;
    } else {
        steps = currentLine.x1 - intersection.x;
    }
    steps *= (steps < 0) ? -1 : 1;
    return steps;
};

//part 2
var part2 = function () {
    var fewestCombinedSteps = null;
    var currentLine1 = {x1: 0, y1: 0, x2: 0, y2: 0};
    var stepsWire1 = 0;
    for (var i = 0; i < wire1.length; i++) {
        prepareCurrentLine(currentLine1, wire1[i]);
        var currentLine2 = {x1: 0, y1: 0, x2: 0, y2: 0};
        var stepsWire2 = 0;
        for (var j = 0; j < wire2.length; j++) {
            prepareCurrentLine(currentLine2, wire2[j]);
            var intersection = getIntersection(currentLine1, currentLine2);
            if(intersection !== false) {
                var stepsLine1 = getStepsForLine(currentLine1, intersection);
                var stepsLine2 = getStepsForLine(currentLine2, intersection);
                var combinedSteps = stepsWire1 + stepsLine1 + stepsWire2 + stepsLine2;
                if(!fewestCombinedSteps || combinedSteps < fewestCombinedSteps) {
                    fewestCombinedSteps = combinedSteps;
                }
            }
            stepsWire2 += wire2[j].distance;
        }
        stepsWire1 += wire1[i].distance;
    }
    console.log("The fewest steps to an intersection is: " + fewestCombinedSteps);
};

part1();
part2();