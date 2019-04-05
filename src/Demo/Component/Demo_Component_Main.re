let str = Yawaramin_ReHyperapp.string;

module Tab = {
  let isActive(stateTab, tab) = if (stateTab == tab) "is-active" else "";

  let make(~currTab, ~code, ~label, ~setTab, _) =
    <a _class=isActive(currTab, code) onclick={(. _event) => setTab(. code)}>
      {str(label)}
    </a>;
};

module Booklist = Demo_Component_Booklist;

type tab = All | ToRead | Reading | Read;
type state = {. tab, booklist: Js.t(Booklist.state)};

type actions = {.
  setTab: (. tab) => {. "tab": tab},
  booklist: Js.t(Booklist.actions),
};
type props = unit;

let state = {"tab": All, "booklist": Booklist.state};

let actions = {
  "setTab": (. tab) => {"tab": tab},
  "booklist": Booklist.actions,
};

let make(~state, ~actions, ~props=(), _) = {
  ignore(props);
  let setTab = actions##setTab;

  <nav _class="panel">
    <p _class="panel-heading">{str("My Library")}</p>
    <div _class="panel-block">
      <p _class="control has-icons-left">
        <input _class="input is-small" _type="text" placeholder="Filter" />
        <span _class="icon is-small is-left">{str({j|🔍|j})}</span>
      </p>
    </div>
    <p _class="panel-tabs">
      <Tab currTab=state##tab code=All label={j|📚 All|j} setTab />
      <Tab currTab=state##tab code=ToRead label={j|📕 To Read|j} setTab />
      <Tab currTab=state##tab code=Reading label={j|📖 Reading|j} setTab />
      <Tab currTab=state##tab code=Read label={j|📗 Read|j} setTab />
    </p>
    <Booklist state=state##booklist actions=actions##booklist />
  </nav>
};
