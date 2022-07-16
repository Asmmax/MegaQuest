@echo off
cd %~dp0/../../
if not exist .venv (
	call scripts/win/setup_venv.bat
)
call .venv/Scripts/activate
echo Generator launch
cd %~dp0/../../utils/generator
python generate.py "C:\Projects\MegaQuest\QuestCore\include" "C:\Projects\MegaQuest\MegaQuestConsole\include" "C:\Projects\MegaQuest\MegaQuestConsole\src" --out_include_dir ".generated" --out_source_dir ".generated"
PAUSE