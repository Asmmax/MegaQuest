from pathlib import Path
import pickle


class ChangesList:
    def __init__(self, file_path: Path):
        self.__file_path = file_path
        self.__changes = {}

    def remove_non_existent(self):
        new_changes = {}
        for file, change in self.__changes.items():
            if file.exists():
                new_changes[file] = change
        self.__changes = new_changes

    def update(self, files: list[Path]):
        for file in files:
            date = file.stat().st_mtime_ns
            self.__changes[file] = date

    def get_changes(self, files: list[Path]) -> list[Path]:
        changed_files = []
        for file in files:
            if self.has_changes(file):
                changed_files.append(file)
        return changed_files

    def has_changes(self, file: Path) -> bool:
        if file not in self.__changes.keys():
            return True
        return self.__changes[file] != file.stat().st_mtime_ns

    def save(self):
        assert self.__file_path is not None
        with open(self.__file_path, 'wb') as changes_file:
            pickle.dump(self, changes_file)

    @staticmethod
    def get_or_create_changes_list(path: Path, file_name: str = 'indices.cache') -> 'ChangesList':
        changes_path = Path(path).joinpath(file_name)
        if not changes_path.exists():
            return ChangesList(changes_path)
        with open(changes_path, 'rb') as changes_file:
            return pickle.load(changes_file)
