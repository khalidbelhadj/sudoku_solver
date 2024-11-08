// WASM
let wasm = null;

function make_env(...envs) {
  return new Proxy(envs, {
    get(target, prop, receiver) {
      for (const env of envs) {
        if (env.hasOwnProperty(prop)) {
          return env[prop];
        }
      }
      return (...args) => {
        console.error("No such function: " + prop);
      };
    },
  });
}

function wasm_init() {
  WebAssembly.instantiateStreaming(fetch("build/main.wasm"), {
    env: make_env(),
  }).then((w0) => {
    wasm = w0;

    const solveButton = document.getElementById("solve");
    solveButton.onclick = () => {
      const c = wasm.instance.exports;
      const game = c.game;

      if (!c.sudoku_solve(game)) {
        alert("No solution found");
      }

      for (let row = 0; row < 9; ++row) {
        for (let col = 0; col < 9; ++col) {
          const value = c.sudoku_get(game, row + 1, col + 1);
          const cell = document.getElementById(`cell-${row}-${col}`);

          if (cell.innerHTML == "") {
            cell.style.color = "green";
          }
          if (value != 0) {
            cell.innerHTML = value;
          }
        }
      }

      sudoku_print();
    };
  });
}

// Initialising grid
let grid = document.getElementById("grid");

wasm_init();

// Creating grid elements
for (let row = 0; row < 9; ++row) {
  for (let col = 0; col < 9; ++col) {
    const cell = document.createElement("div");
    grid.appendChild(cell);

    cell.setAttribute("id", `cell-${row}-${col}`);
    cell.setAttribute("tabindex", "0");

    // Thick borders
    if (col % 3 == 0) cell.style.borderLeft = "2px solid black";
    if (col === 8) cell.style.borderRight = "2px solid black";
    if (row % 3 == 0) cell.style.borderTop = "2px solid black";
    if (row === 8) cell.style.borderBottom = "2px solid black";

    cell.onkeydown = (event) => {
      const c = wasm.instance.exports;
      const game = c.game;

      if (/^[1-9]$/.test(event.key)) {
        const result = c.sudoku_set(
          game,
          row + 1,
          col + 1,
          parseInt(event.key)
        );

        if (result) {
          cell.innerHTML = event.key;
        } else {
          console.error("did not set", parseInt(event.key));
          sudoku_print(game);
        }
        sudoku_print();
      } else if (event.key === "Backspace") {
        event.innerHTML = "";
        c.sudoku_unset(game, row + 1, col + 1);
      } else if (event.key === "ArrowUp") {
        const next_cell = document.getElementById(`cell-${row - 1}-${col}`);
        next_cell.focus();
      } else if (event.key === "ArrowDown") {
        const next_cell = document.getElementById(`cell-${row + 1}-${col}`);
        next_cell.focus();
      } else if (event.key === "ArrowLeft") {
        const next_cell = document.getElementById(`cell-${row}-${col - 1}`);
        next_cell.focus();
      } else if (event.key === "ArrowRight") {
        const next_cell = document.getElementById(`cell-${row}-${col + 1}`);
        next_cell.focus();
      }
      console.log(event.key);
    };

    cell.onfocus = () => {
      cell.style.backgroundColor = "#e3e3e3";
      cell.style.outline = "none";
    };

    cell.onclick = () => {
      cell.focus();
    };

    cell.onblur = () => {
      cell.style.backgroundColor = "white";
    };
  }
}

const resetButton = document.getElementById("reset");
resetButton.onclick = () => {
  const c = wasm.instance.exports;
  const game = c.game;

  for (let row = 0; row < 9; ++row) {
    for (let col = 0; col < 9; ++col) {
      const cell = document.getElementById(`cell-${row}-${col}`);
      cell.innerHTML = "";
      c.sudoku_unset(game, row + 1, col + 1);
      cell.style.color = "black";
    }
  }
};

function sudoku_print() {
  const c = wasm.instance.exports;
  const game = c.game;
  let output = "";

  output += "----------------------\n";

  for (let row = 1; row <= 9; ++row) {
    output += "|";

    for (let col = 1; col <= 9; ++col) {
      const value = c.sudoku_get(game, row, col);

      if (value == 0) {
        output += "  ";
      } else {
        output += `${value} `;
      }

      if (col % 3 == 0) {
        output += "|";
      }
    }

    if (row % 3 == 0) {
      output += "\n----------------------";
    }
    output += "\n";
  }
  console.log(output);
}
