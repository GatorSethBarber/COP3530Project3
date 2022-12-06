const tableBody = document.getElementById('tableBody');
const salaryInput = document.getElementById('inputSalary');
const educationInput = document.getElementById('inputEducation');
const experienceInput = document.getElementById('inputExperience');
const alternateSortCheck = document.getElementById('datasetSwitch');
const jobGrowthSlide = document.getElementById('inputJobGrowth');

const addRow = (occupation, salary, education, experience, jobGrowth) => {
    let row = tableBody.insertRow();
    let occCell = row.insertCell(0);
    occCell.innerHTML = occupation;
    let salCell = row.insertCell(1);
    salCell.innerHTML = salary;
    let eduCell = row.insertCell(2);
    eduCell.innerHTML = education;
    let experCell = row.insertCell(3);
    experCell.innerHTML = experience;
}

const formValidation = (inputValues) => {
    for (let i = 0; i < inputValues.length; i++) {
        if (inputValues[i] == "") {
            alert("Must supply information concerning all fields.");
            return false;
        }
    }

    return true;
}

const clearTable = () => {
    // https://www.javascripttutorial.net/dom/manipulating/remove-all-child-nodes/
    while (tableBody.firstChild) {
        tableBody.removeChild(tableBody.firstChild);
    }
}

const populateTable = (twoDArray) => {
    clearTable();
    for (let i = 0; i < twoDArray.length; i++) {
        addRow(...twoDArray[i]);
    }
}