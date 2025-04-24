lua << EOF
vim.api.nvim_set_keymap(
    "n",
    "<F5>",
    ":silent !osascript -e 'tell application \"Terminal\" to do script \"cd " .. vim.fn.getcwd() .. " && make && ./build/heliarch_v1\"'<CR>",
    { noremap = true, silent = true }
)
EOF

