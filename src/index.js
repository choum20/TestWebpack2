import sum from "./function/sum";

console.log(sum());
console.log(process.env.NODE_ENV);
let bang = document.querySelector(".bang");
bang.innerHTML = sum();