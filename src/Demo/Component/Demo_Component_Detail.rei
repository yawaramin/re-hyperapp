module Domain = Demo_Domain;

include Yawaramin_ReHyperapp.Component.Type with
  type props = option(Domain.Book.t)
  and type actions = {.
    reset: (. unit) => {.
      "author": option(string),
      "description": option(string),
      "title": option(string),
      "status": option(Domain.Status.t),
    },
    setAuthor: (. string) => {. "author": option(string)},
    setDescription: (. string) => {. "description": option(string)},
    setTitle: (. string) => {. "title": option(string)},
    setStatus: (. string) => {. "status": option(Domain.Status.t)},
  };
