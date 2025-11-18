#!/bin/bash
# Generate VSCode launch.json for all main.cpp files in the project

set -e

WORKSPACE_DIR="${1:-/workspaces/$(basename $(pwd))}"
VSCODE_DIR="${WORKSPACE_DIR}/.vscode"
LAUNCH_FILE="${VSCODE_DIR}/launch.json"

# Create .vscode directory if it doesn't exist
mkdir -p "${VSCODE_DIR}"

echo "Searching for main.cpp files..."

# Find all main.cpp files and generate configurations
CONFIGS=""
FIRST=true

while IFS= read -r -d '' main_file; do
    # Get directory containing main.cpp
    main_dir=$(dirname "$main_file")

    # Get relative path from workspace root
    rel_path=$(realpath --relative-to="${WORKSPACE_DIR}" "$main_dir")

    # Generate executable name (replace / with _)
    exec_name=$(echo "$rel_path" | tr '/' '_')

    # Get relative cwd
    rel_cwd="\${workspaceFolder}/${rel_path}"

    echo "  Found: ${exec_name} (${rel_path})"

    # Add comma if not first config
    if [ "$FIRST" = false ]; then
        CONFIGS="${CONFIGS},"
    fi
    FIRST=false

    # Generate configuration JSON
    CONFIGS="${CONFIGS}
        {
            \"name\": \"Debug: ${exec_name}\",
            \"type\": \"cppdbg\",
            \"request\": \"launch\",
            \"program\": \"\${workspaceFolder}/build/${exec_name}\",
            \"args\": [],
            \"stopAtEntry\": false,
            \"cwd\": \"${rel_cwd}\",
            \"environment\": [],
            \"externalConsole\": false,
            \"MIMode\": \"gdb\",
            \"setupCommands\": [
                {
                    \"description\": \"Enable pretty-printing for gdb\",
                    \"text\": \"-enable-pretty-printing\",
                    \"ignoreFailures\": true
                }
            ],
            \"preLaunchTask\": \"CMake: Build All\",
            \"miDebuggerPath\": \"/usr/bin/gdb\"
        }"
done < <(find "${WORKSPACE_DIR}" -name "main.cpp" -type f -print0 | sort -z)

# Generate complete launch.json
cat > "${LAUNCH_FILE}" <<EOF
{
    "version": "0.2.0",
    "configurations": [${CONFIGS}
    ]
}
EOF

echo ""
echo "✓ Generated ${LAUNCH_FILE}"
echo ""
echo "Found $(echo "$CONFIGS" | grep -c '"name"') executable(s)"
echo ""
echo "Usage:"
echo "  1. Press Ctrl+Shift+B to build all executables"
echo "  2. Press F5 to start debugging"
echo "  3. Select which executable to debug from the dropdown"