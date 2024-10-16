from setuptools import setup, find_packages


def read_requirements(path):
    requires = []
    with open(path) as f:
        for l in f.readlines():
            l = l.strip()
            if l[:1] == "#":
                continue
            requires.append(l)
    return requires


setup(
    name="reccmp",
    version="0.1.0",
    description="Python tools for the isledecomp project",
    packages=find_packages(),
    install_requires=read_requirements("requirements.txt"),
    tests_require=read_requirements("requirements-tests.txt"),
    include_package_data=True,
    package_data={"isledecomp.lib": ["*.exe", "*.dll"]},
)
