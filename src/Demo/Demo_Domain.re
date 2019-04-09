module Book = {
  type id = string;
  type status = [`ToRead | `Reading | `Read];

  type t = {.
    "author": string,
    "description": string,
    "id": id,
    "title": string,
    "status": status,
  };
};
