module Book = {
  type id = string;

  type t = {.
    "author": string,
    "description": string,
    "id": id,
    "title": string,
  };
};
