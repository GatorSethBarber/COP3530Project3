const tableBody = document.getElementById('tableBody');
const salaryInput = document.getElementById('inputSalary');
const educationInput = document.getElementById('inputEducation');
const experienceInput = document.getElementById('inputExperience');
const alternateSortCheck = document.getElementById('datasetSwitch');
const jobGrowthSlide = document.getElementById('inputJobGrowth');

/**
 * Add row to the table
 * @param {*} array An array to add in to the table
 */
const addRow = (array) => {
    console.log(array);
    let row = tableBody.insertRow();
    for (let i = 0; i < array.length; i++) {
        let newCell = row.insertCell(i);
        newCell.innerHTML = array[i];
    }
}

/**
 * Make sure all forms have been filled out.
 * @param {*} inputValues 
 * @returns A boolean indicating success or failure
 */
const formValidation = (inputValues) => {
    for (let i = 0; i < inputValues.length; i++) {
        if (inputValues[i] == "") {
            alert("Must supply information concerning all fields.");   // Display a message
            return false;
        }
    }

    return true;
}

/**
 * Clear the table of any information it currently holds.
 */
const clearTable = () => {
    // https://www.javascripttutorial.net/dom/manipulating/remove-all-child-nodes/
    while (tableBody.firstChild) {
        tableBody.removeChild(tableBody.firstChild);
    }
}

/**
 * Populate the table based on data returned from the server.
 * @param {*} twoDArray 
 */
const populateTable = (twoDArray) => {
    clearTable();
    for (let i = 0; i < twoDArray.length; i++) {
        twoDArray[i][3] = Number(twoDArray[i][3]).toFixed(1);
        addRow(twoDArray[i]);
    }
}