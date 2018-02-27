type books = array({.
  "id": int,
  "copies": int,
  "title": string,
  "author": string,
  "description": string
});

let actions = {"set": [@bs] ((books: books) => {value: Some(books)})};

let view(state) = Hyperapp.h("span", [||]);
