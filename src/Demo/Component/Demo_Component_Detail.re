module Hy = Yawaramin_ReHyperapp;
module Domain = Demo_Domain;

type state = {.
  author: string,
  description: string,
  title: string,
};

type actions = {.
  setAuthor: (. string) => {. "author": string},
  setDescription: (. string) => {. "description": string},
  setTitle: (. string) => {. "title": string},
};

type props = option(Domain.Book.t);

let state = {"author": "", "description": "", "title": ""};

let actions = {
  "setAuthor": (. author) => {"author": author},
  "setDescription": (. description) => {"description": description},
  "setTitle": (. title) => {"title": title},
};

let make(~state as _=state, ~actions as _=actions, ~props, _children) = {
  let book = props |> Js.Option.getWithDefault({
    "author": "",
    "description": "",
    "id": "(None)",
    "title": "",
    "status": `ToRead,
  });

  <div _class="tile is-parent">
    <div _class="tile is-child box">
      <div _class="field">
        <label _class="label">{Hy.string("ID")}</label>
        <p _class="content">{Hy.string(book##id)}</p>
      </div>
      <div _class="field">
        <label _class="label">{Hy.string({j|❡ Title|j})}</label>
        <div _class="control">
          <input _class="input" _type="text" value=book##title />
        </div>
      </div>
      <div _class="field">
        <label _class="label">{Hy.string({j|🗣 Author(s)|j})}</label>
        <div _class="control">
          <input _class="input" _type="text" placeholder="Joe Q. Author" value=book##author />
        </div>
      </div>
      <div _class="field">
        <label _class="label">{Hy.string({j|📝 Description|j})}</label>
        <div _class="control">
          <textarea _class="textarea" placeholder="A nice description of the document" value=book##description />
        </div>
      </div>
    </div>
  </div>;
};
