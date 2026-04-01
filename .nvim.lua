vim.cmd("cd " .. vim.fn.fnamemodify(vim.fn.resolve(debug.getinfo(1).source:sub(2)), ":h") .. "/build")
