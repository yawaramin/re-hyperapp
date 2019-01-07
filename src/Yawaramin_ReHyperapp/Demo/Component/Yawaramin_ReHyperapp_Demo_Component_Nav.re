type state = {. "query": string};
type actions = {. "setQuery": (. string) => state};

let state = {"query": ""};

let actions: actions = {
  "setQuery": (. string) => {
    Js.log2("Query is:", string);
    {query: string};
  },
};

let handleSearch(state, actions) = (. event) =>
  switch (event##which, event##target##value) {
  | (_, "") => state
  | (13, query) => let action = actions##setQuery; action(. query)
  | _ => state
  };

let string = Yawaramin_ReHyperapp.string;

let make(~state: state, ~actions: actions, _childen) =
  <nav _class="navbar is-dark" role="navigation">
    <div _class="navbar-brand">
      <a _class="navbar-item" href="#">
        <img src="http://via.placeholder.com/150x20" alt="Placeholder Logo" width="150px" height="20px" />
      </a>
    </div>
    <div _class="navbar-menu is-active">
      <div _class="navbar-start">
        <div _class="navbar-item">{string("Search Library:")}</div>
        <div _class="navbar-item">
          <div _class="field">
            <div _class="control is-expanded">
              <input
                _class="input is-normal"
                _type="text"
                onkeypress={handleSearch(state, actions)}
                placeholder="Search Library" />
            </div>
          </div>
        </div>
      </div>
    </div>
  </nav>;
