function submitQuestionnaire() {
    const table = document.getElementById("tableBody");
    let row = table.insertRow();
    let occupation = row.insertCell(0);
    occupation.innerHTML = "test";
    let salary = row.insertCell(1);
    salary.innerHTML = document.getElementById("inputSalary").value;
    let education = row.insertCell(2);
    education.innerHTML = document.getElementById("inputEducation").value;
    let workExperience = row.insertCell(3);
    workExperience.innerHTML = document.getElementById("inputExperience").value;
}