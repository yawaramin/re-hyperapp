type book = {.
  "id": int,
  "copies": int,
  "title": string,
  "author": string,
  "description": string
};

type state = {. "value": option(array(book))};

let state = {"value": None};

let actions = {
  "set": [@bs] (books: array(book)) => {value: Some(books)}
};

let view(_) = Hyperapp.h("span", [||]);
