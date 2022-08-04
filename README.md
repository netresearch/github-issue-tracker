# GitHub issue tracker

IOT project to monitor the amount of GitHub issues of a organisation.

## Requirements

### Hardware

- [ ] A4 Picture frame
- [ ] ESP 8266 Wemos D1 mini
- [ ] Power supply unit
- [ ] Battery with voltage regulator
- [ ] 7 segment display 4 digits

### Tools

- **Soldering**
  - [ ] Soldering iron
  - [ ] Soldering grease
  - [ ] Tin
  - [ ] Helping Hand
- **Cable**
  - [ ] Data cable 25AWG
  - [ ] Power cable 25AWG
  - [ ] Micro USB cable
  - [ ] Type C USB cable
- [ ] Power supply USB Type C
  
### Software requirements

- VSCode
- PlatformIO plugin
- USB serial driver (MacOS, Windows)

## Software

- [ ] OTA
- [ ] Configurable
  - [ ] Organisation
  - [ ] Token
- [ ] Deep Sleep
- [ ] Battery monitoring
- [ ] Polling GitHub API
  - [ ] https://docs.github.com/en/rest/issues/issues#list-repository-issues
  - [ ] gh api -H "Accept: application/vnd.github+json" /orgs/netresearch/repos

## GraphQL

https://docs.github.com/en/graphql/overview/explorer

```gql
{
  viewer {
    login
    email
    organizations(first:100) {
      nodes {
        name,
        repositories(first:100) {
          nodes {
            description
          }
        }
      }
    }
  }
}
```

## Documentation

### GitHub Repository

- [ ] Description
- [ ] Rebuild instructions
- [ ] C++ software

### Photos

- [ ] Parts overview
- [ ] Assembly
- [ ] Result
- [ ] NR Logo

### Video

- [ ] Live coding
- [ ] Hardware assembling
- [ ] Documentation
- [ ] Room recording (participants)

### Sound

- [ ] Coding (meet/discord)
- [ ] Participants
- [ ] Hardware

## Roles

- [ ] Software developer
- [ ] Hardware
  - [ ] IOT solderer
  - [ ] Picture frame hobbyist
- [ ] Documentation (+ Moderator)
  - [ ] Repo
  - [ ] Photos
  - [ ] Video editor


