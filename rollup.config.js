import commonjs from 'rollup-plugin-commonjs';
import node_resolve from 'rollup-plugin-node-resolve';
import uglify from 'rollup-plugin-uglify';

export default {
  input: './src/Index.bs.js',
  output: {
    name: 'index',
    file: './build/index.js',
    format: 'iife'
  },
  plugins: [
    node_resolve({module: true, browser: true}),
    commonjs({sourceMap: false}),
    //uglify()
  ]
}
