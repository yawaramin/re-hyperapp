module Hy = Yawaramin_ReHyperapp;
module Domain = Demo_Domain;

type state = {.
  author: option(string),
  description: option(string),
  title: option(string),
  status: option(Domain.Status.t),
};

type actions = {.
  reset: (. unit) => Js.t(state),
  setAuthor: (. string) => {. "author": option(string)},
  setDescription: (. string) => {. "description": option(string)},
  setTitle: (. string) => {. "title": option(string)},
  setStatus: (. string) => {. "status": option(Domain.Status.t)},
};

type props = option(Domain.Book.t);

let state = {
  "author": None,
  "description": None,
  "title": None,
  "status": None,
};

let actions = {
  "reset": (. ) => state,
  "setAuthor": (. author) => {"author": Some(author)},
  "setDescription": (. description) => {"description": Some(description)},
  "setTitle": (. title) => {"title": Some(title)},
  "setStatus": (. status) => {"status": Domain.Status.fromString(status)},
};

let (or) = Belt.Option.getWithDefault;

let make(~state=state, ~actions=actions, ~props, _children) = {
  let author = state##author or Js.Option.map((. book) => book##author, props) or "";
  let description = state##description or Js.Option.map((. book) => book##description, props) or "";
  let id = Js.Option.map((. book) => book##id, props) or "(None)";
  let title = state##title or Js.Option.map((. book) => book##title, props) or "";
  let _status = state##status or Js.Option.map((. book) => book##status, props) or `ToRead;
  let setAuthor = actions##setAuthor;
  let setDescription = actions##setDescription;
  let setTitle = actions##setTitle;

  <div _class="tile is-parent">
    <div _class="tile is-child box">
      <div _class="field">
        <label _class="label">{Hy.string("ID")}</label>
        <p _class="content">{Hy.string(id)}</p>
      </div>
      <div _class="field">
        <label _class="label">{Hy.string({j|❡ Title|j})}</label>
        <div _class="control">
          <input
            _class="input"
            _type="text"
            value=title
            onblur={(. event) => setTitle(. event##target##value)} />
        </div>
      </div>
      <div _class="field">
        <label _class="label">{Hy.string({j|🗣 Author(s)|j})}</label>
        <div _class="control">
          <input
            _class="input"
            _type="text"
            placeholder="Joe Q. Author"
            value=author
            onblur={(. event) => setAuthor(. event##target##value)} />
        </div>
      </div>
      <div _class="field">
        <label _class="label">{Hy.string({j|📝 Description|j})}</label>
        <div _class="control">
          <textarea
            _class="textarea"
            placeholder="A nice description of the document"
            value=description
            onblur={(. event) => setDescription(. event##target##value)} />
        </div>
      </div>
      <div _class="field">
        <label _class="label">{Hy.string({j|📚 Status|j})}</label>
        <div _class="control has-icons-left">
          <div _class="select">
            <select>
              <option selected=true>{Hy.string("read")}</option>
            </select>
          </div>
          <span _class="icon is-left">{Hy.string({j|📗|j})}</span>
        </div>
      </div>
    </div>
  </div>;
};
